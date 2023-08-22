using Microsoft.AspNetCore.SignalR;
using WebApp.Models;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace WebApp.Hubs {
   public class UnitHub : Hub<IUnitData> {
      public async void BroadcastUnitState(UnitState unitState) {
         await Clients.All.GetUnitState(unitState).ConfigureAwait(false);
      }
      public async void BroadcastTempSensors(OperationState operationState) {
         await Clients.All.GetOperationState(operationState).ConfigureAwait(false);
      }
   }
}
