using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using Microsoft.AspNetCore.SignalR;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;
using Microsoft.Extensions.Primitives;
using WebApp.Hubs;
using WebApp.Models;

namespace WorkerService {
   public class Worker : BackgroundService {

      // Constants

      // Data header type US: UnitState|OS: OperatingState
      private const int Header = 0;

      // Unit state data
      private const int Status = 1;
      private const int Auto = 2;
      private const int Econ = 3;
      private const int Reci = 4;
      private const int AirDistMotor = 5;
      private const int SelectedTemp = 6;
      private const int BlowSpeed = 7;
      private const int SymEXT = 8;

      // Operation state data
      private const int Vref = 1;
      private const int ThreeLevelSwitch = 2;
      private const int OutsideTemp = 3;
      private const int PassengerTemp = 4;
      private const int TopTemp = 5;
      private const int BottomTemp = 6;

      // DI
      private readonly ILogger<Worker> m_logger;
      private readonly IHubContext<UnitHub, IUnitData> m_hubContext;

      //Serial Port
      private SerialPort m_serialPort;
      private readonly string m_port;
      private readonly int m_baud;

      public Worker(ILogger<Worker> logger, IConfiguration configuration, IHubContext<UnitHub, IUnitData> hubContext) {
         m_logger = logger;
         m_hubContext = hubContext;

         // Read from appsettings.json
         m_port = configuration.GetSection("SerialPort").GetValue<string>("Port");
         m_baud = configuration.GetSection("SerialPort").GetValue<int>("BaudRate");
      }

      private void OpenSerialPort() {
         try {
            m_logger.LogInformation($"Open Serial Port {m_port} at baud rate of {m_baud} bps");

            m_serialPort = new SerialPort {
               PortName = m_port,
               BaudRate = m_baud,
               DataBits = 8,
               Parity = Parity.None,
               StopBits = StopBits.One,
               Handshake = Handshake.None,
               ReadBufferSize = 500,
               WriteBufferSize = 500,
               ReadTimeout = 250,
               WriteTimeout = 250
            };

            m_serialPort.Open();
            if (m_serialPort.IsOpen) {
               m_logger.LogInformation($"Serial Port {m_port} opened");
            }
         }
         catch (Exception e) {
            m_logger.LogError(e.Message);
         }
      }
      private void CloseSerialPort() {
         try {
            m_logger.LogInformation($"Closing Serial Port {m_port}");
            m_serialPort?.Close();

            if (!m_serialPort.IsOpen) {
               m_logger.LogInformation($"Serial Port {m_port} closed");
            }
         }
         catch (Exception e) {
            m_logger.LogError(e.Message);
         }
         finally {
            m_serialPort?.Dispose();

            m_logger.LogInformation($"Exiting service");
         }
      }
      public override Task StartAsync(CancellationToken cancellationToken) {
         OpenSerialPort();

         return base.StartAsync(cancellationToken);
      }

      public override Task StopAsync(CancellationToken cancellationToken) {
         CloseSerialPort();

         return base.StopAsync(cancellationToken);
      }

      protected override async Task ExecuteAsync(CancellationToken stoppingToken) {

         while (!stoppingToken.IsCancellationRequested) {
            m_logger.LogInformation("Running: {time}", DateTimeOffset.Now);

            try {

               //Read from Serial Port and Process line
               //string[] strs = m_serialPort?.ReadLine().Split("|");
               StringValues strs = m_serialPort?.ReadLine().Split("|");
               if (strs[Header].Equals("US")) {

                  int adm = Int32.Parse(strs[AirDistMotor]);   // Air Dist. Motor

                  UnitState unitState = new UnitState {
                     LedOn = strs[Status].Equals("1"),
                     LedAuto = strs[Auto].Equals("1"),
                     LedEcon = strs[Econ].Equals("1"),
                     LedReci = strs[Reci].Equals("1"),
                     LedOff = !strs[Status].Equals("1"),
                     LedFront = adm == 0,
                     LedFrontFeet = adm == 1,
                     LedFeet = adm == 2,
                     LedWindshield = adm == 3,
                     SelectedTemp = Int32.Parse(strs[SelectedTemp]),
                     BlowSpeed = Int32.Parse(strs[BlowSpeed]),
                     SymEXT = strs[SymEXT].Equals("1"),
                     SymMANUAL = !strs[Auto].Equals("1"),
                     SymAUTO = strs[Auto].Equals("1")
                  };

                  // Broadcast new messages to client
                  m_logger.LogInformation("Broadcasting UnitState: {0}", String.Join(',', strs));
                  await m_hubContext.Clients.All.GetUnitState(unitState).ConfigureAwait(false);
               }

               if (strs[Header].Equals("OS")) {
                  // OS: Temp Sensor info
                  OperationState operationState = new OperationState {
                     Vref = Single.Parse(strs[Vref]),
                     ThreeLevelSwitch = Int32.Parse(strs[ThreeLevelSwitch]),
                     OutsideTemp = Int32.Parse(strs[OutsideTemp]),
                     PassengerTemp = Int32.Parse(strs[PassengerTemp]),
                     TopTemp = Int32.Parse(strs[TopTemp]),
                     BottomTemp = Int32.Parse(strs[BottomTemp])
                  };

                  m_logger.LogInformation("Broadcasting OperationState: {0}", String.Join(',', strs));
                  await m_hubContext.Clients.All.GetOperationState(operationState).ConfigureAwait(false);
               }
            }
            catch (TimeoutException e) {
               m_logger.LogError(e.Message);
            }
            catch (Exception e) {
               m_logger.LogError(e.Message);

               // Could be
               if (!m_serialPort.IsOpen) {
                  OpenSerialPort();
               }
            }

            await Task.Delay(500, stoppingToken).ConfigureAwait(false);
         }
      }
   }
}
