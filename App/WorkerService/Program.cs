using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Serilog;
using Serilog.Events;

namespace WorkerService {
   public static class Program {
      public static void Main(string[] args) {

         Log.Logger = new LoggerConfiguration().
                          MinimumLevel.Debug().
                          MinimumLevel.Override("Microsoft", LogEventLevel.Warning).
                          Enrich.FromLogContext().
                          WriteTo.File(
                             @"X:\Development\IoT SolucioneX\ElectronicAAUnitAVR8\SerialPortService\service.log",
                             fileSizeLimitBytes: 1_000_000,
                             rollOnFileSizeLimit: true,
                             shared: true,
                             flushToDiskInterval: TimeSpan.FromSeconds(1)).
                          CreateLogger();

         try {
            Log.Information("Starting A/A Unit Service Serial Communication");
            CreateHostBuilder(args).Build().Run();

            return;
         }
         catch (Exception ex) {
            Log.Fatal(ex, "A/A Unit Service Serial Communication terminated unexpectedly");

            return;
         }
         finally {
            Log.CloseAndFlush();
         }
      }

      public static IHostBuilder CreateHostBuilder(string[] args) =>
          Host.CreateDefaultBuilder(args) .
               ConfigureServices((hostContext, services) => {
                 services.AddHostedService<Worker>();
               }).
               UseWindowsService().
               UseSerilog();
   }
}
