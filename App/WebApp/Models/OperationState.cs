using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace WebApp.Models {
   public class OperationState {

      // Voltage reference
      public float Vref { get; set; }

      // Three Level Pressure Switch (Compressor Pulley)
      public int ThreeLevelSwitch { get; set; }

      // Temp. Sensors info
      public int OutsideTemp { get; set; }
      public int PassengerTemp { get; set; }
      public int BottomTemp { get; set; }
      public int TopTemp { get; set; }
   }
}
