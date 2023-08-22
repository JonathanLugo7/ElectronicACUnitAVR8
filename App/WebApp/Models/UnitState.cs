using System.Collections.Generic;

namespace WebApp.Models {
   public class UnitState {

      // LED status
      public bool LedOn { get; set; }
      public bool LedAuto { get; set; }
      public bool LedEcon { get; set; }
      public bool LedReci { get; set; }
      public bool LedOff { get; set; }

      // LED air distribution position
      public bool LedWindshield { get; set; }
      public bool LedFront { get; set; }
      public bool LedFrontFeet { get; set; }
      public bool LedFeet { get; set; }

      // Temp
      public int SelectedTemp { get; set; }

      // Speed
      public int BlowSpeed { get; set; }

      // LCD Symbols
      public bool SymMANUAL { get; set; }
      public bool SymAUTO { get; set; }
      public bool SymEXT { get; set; }
   }
}
