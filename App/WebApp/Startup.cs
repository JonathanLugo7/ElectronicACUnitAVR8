using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.HttpOverrides;
using Microsoft.AspNetCore.HttpsPolicy;
using Microsoft.AspNetCore.SpaServices.AngularCli;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using System.Net;
using WebApp.Hubs;
using WorkerService;

namespace WebApp {
   public class Startup {
      public Startup(IConfiguration configuration) {
         Configuration = configuration;
      }

      public IConfiguration Configuration { get; }

      // This method gets called by the runtime. Use this method to add services to the container.
      public void ConfigureServices(IServiceCollection services) {

         // Set CORS operations
         services.AddCors(options => {
            options.AddPolicy("CorsPolicy", builder =>
               builder.WithOrigins("http://localhost:4200").
                       AllowAnyMethod().
                       AllowAnyHeader().
                       AllowCredentials());
         });

         // Trusted reverse proxy (Configured with Apache)
         services.Configure<ForwardedHeadersOptions>(configureOptions => {
            configureOptions.ForwardLimit = 2;
            configureOptions.ForwardedHeaders = ForwardedHeaders.XForwardedFor | ForwardedHeaders.XForwardedProto;
            configureOptions.KnownProxies.Add(IPAddress.Parse("127.0.0.1"));
         });

         // Add SignalR
         services.AddSignalR(options => {
               options.EnableDetailedErrors = true;
            }).AddJsonProtocol(configure => {
               configure.PayloadSerializerOptions.PropertyNamingPolicy = null;
            });

         // Add worker services for broadcast message from BackgroundService using SignalR
         services.AddHostedService<Worker>();

         //
         services.AddControllersWithViews();

         // In production, the Angular files will be served from this directory
         services.AddSpaStaticFiles(configuration => {
            configuration.RootPath = "ClientApp/dist";
         });
      }

      // This method gets called by the runtime. Use this method to configure the HTTP request pipeline.
      public void Configure(IApplicationBuilder app, IWebHostEnvironment env) {
         if (env.IsDevelopment()) {
            app.UseDeveloperExceptionPage();
         }
         else {
            app.UseExceptionHandler("/Error");
            // The default HSTS value is 30 days. You may want to change this for production scenarios, see https://aka.ms/aspnetcore-hsts.
            app.UseHsts();
         }

         // For Reverse Proxy use (Configured with Apache)
         app.UseForwardedHeaders(new ForwardedHeadersOptions {
             ForwardedHeaders = ForwardedHeaders.XForwardedFor | ForwardedHeaders.XForwardedProto
         });

         app.UseHttpsRedirection();

         app.UseStaticFiles(new StaticFileOptions() {
            HttpsCompression = Microsoft.AspNetCore.Http.Features.HttpsCompressionMode.Compress,
            OnPrepareResponse = (context) => {
               context.Context.Response.Headers.Add("Cache-Control", Configuration["StaticFiles:Cache:Cache-Control"]);
               context.Context.Response.Headers.Add("Pragma", Configuration["StaticFiles:Cache:Pragma"]);
               context.Context.Response.Headers.Add("Expires", Configuration["StaticFiles:Cache:Expires"]);
            }
         });

         if (!env.IsDevelopment()) {
            app.UseSpaStaticFiles();
         }

         app.UseRouting();

         app.UseCors("CorsPolicy");

         app.UseEndpoints(endpoints => {
            endpoints.MapControllerRoute(
                name: "default",
                pattern: "{controller}/{action=Index}/{id?}");

            // SignalR route
            endpoints.MapHub<UnitHub>("/unitdata");
         });

         app.UseSpa(spa => {
            // To learn more about options for serving an Angular SPA from ASP.NET Core,
            // see https://go.microsoft.com/fwlink/?linkid=864501

            spa.Options.SourcePath = "ClientApp";

            if (env.IsDevelopment()) {
               //spa.UseAngularCliServer(npmScript: "start");
               spa.UseProxyToSpaDevelopmentServer("http://localhost:4200");
            }
         });
      }
   }
}
