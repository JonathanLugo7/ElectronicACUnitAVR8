using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;

namespace WorkerService {
   public class Worker : BackgroundService {
      private readonly ILogger<Worker> _logger;
      private SerialPort m_serialPort;

      private const string m_port = "COM1";
      private const int m_baud = 38400;

      public Worker(ILogger<Worker> logger) {
         _logger = logger;
      }

      public override Task StartAsync(CancellationToken cancellationToken) {

         try {
            _logger.LogInformation($"Open Serial Port {m_port} at baud rate of {m_baud} bps");

            m_serialPort = new SerialPort {
               PortName = m_port,
               BaudRate = m_baud,
               DataBits = 8,
               Parity = Parity.None,
               StopBits = StopBits.One,
               Handshake = Handshake.None,
               ReadBufferSize = 500,
               ReadTimeout = 500,
               WriteBufferSize = 500,
               WriteTimeout = 500
            };

            m_serialPort.Open();
         }
         catch (Exception e) {
            _logger.LogError(e.Message);
         }

         return base.StartAsync(cancellationToken);
      }

      public override Task StopAsync(CancellationToken cancellationToken) {

         try {
            _logger.LogInformation($"Closing Serial Port {m_port}");
            m_serialPort?.Close();
         }
         catch (Exception e) {
            _logger.LogError(e.Message);
         }
         finally {
            m_serialPort?.Dispose();

            _logger.LogInformation($"Exiting service");
         }

         return base.StopAsync(cancellationToken);
      }

      protected override async Task ExecuteAsync(CancellationToken stoppingToken) {
         while (!stoppingToken.IsCancellationRequested) {
            _logger.LogInformation("Running: {time}", DateTimeOffset.Now);

            try {
               string str = m_serialPort?.ReadLine();
            }
            catch (TimeoutException e) {
               _logger.LogError(e.Message);
            }
            catch (Exception e) {
               _logger.LogError(e.Message);
            }

            await Task.Delay(30*1000, stoppingToken);
         }
      }
   }
}
