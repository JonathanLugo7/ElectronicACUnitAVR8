using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using WebApp.Models;

namespace WebApp.Hubs {
   public interface IUnitData {
      Task GetUnitState(UnitState unitData);
      Task GetOperationState(OperationState operationState);
   }
}
