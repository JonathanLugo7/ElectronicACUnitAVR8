import { Injectable, Inject } from '@angular/core';
import { Subject } from 'rxjs';
import * as signalR from '@microsoft/signalr';

import { UnitState } from '../interfaces/unit-state.model';
import { OperationState } from '../interfaces/operation-state.model';

@Injectable({
   providedIn: 'root',
})
export class SignalRService {
   // SignalR hub connection
   private hubConnection: signalR.HubConnection;

   // Shared in app.componet.ts
   public messages: string[];
   public unitState: UnitState;
   public operationState: OperationState;
   public displayTemp = '-188';

   // Create observable source for calling component function
   private source = new Subject<any>();
   public observable$ = this.source.asObservable();

   constructor(@Inject('BASE_URL') private baseUrl: string) {
      console.log('SignalRService <constructor>');

      this.messages = ['Unit off', 'Ready...'];

      // Create objects
      this.unitState = {
         LedOn: false,
         LedAuto: false,
         LedEcon: false,
         LedReci: false,
         LedOff: true,
         LedWindshield: false,
         LedFront: false,
         LedFrontFeet: false,
         LedFeet: false,
         SymMANUAL: false,
         SymAUTO: false,
         SymEXT: false,
         SelectedTemp: 0,
         BlowSpeed: 0
      };

      this.operationState = {
         Vref: 0,
         ThreeLevelSwitch: 0,
         OutsideTemp: 0,
         PassengerTemp: 0,
         BottomTemp: 0,
         TopTemp: 0,
      };
   }

   public startConnection = (): void => {
      console.log('SignalRService <startConnection>');
      console.log('|- URL: ' + this.baseUrl + ' / unitdata');

      this.hubConnection = new signalR.HubConnectionBuilder()
         .withUrl(this.baseUrl + '/unitdata')
         .withUrl('/unitdata')
         .withAutomaticReconnect()
         .build();

      this.hubConnection
         .start()
         .then(() => console.log('|- Connection started'))
         .catch((err) =>
            console.log('|- Error while starting connection: ' + err)
         );
   }

   public addUnitStateListener = (): void => {
      console.log('SignalRService <addUnitStateListener>');

      this.hubConnection.on('getunitstate', (data) => {
         this.unitState = data;

         this.checkTemperature();

         // Call AppComponent function. "Scroll console to last message"
         this.messages.push('New unit state data arrived. Unit: ' + (this.unitState.LedOn ? 'ON' : 'OFF') +
                                                       '. Ext.: ' + (this.unitState.SymEXT ? 'ON' : 'OFF'));
         this.source.next('New unit state data arrived');
      });
   }

   public addOperationStateListener = (): void => {
      console.log('SignalRService <addOperationStateListener>');

      this.hubConnection.on('getoperationstate', (data) => {
         this.operationState = data;

         this.checkTemperature();

         // Call AppComponent function. "Scroll console to last message"
         this.messages.push(`New operation state data arrived. Unit Vref: ${this.operationState.Vref}`);
         this.source.next('New operation state data arrived');
      });
   }

   private checkTemperature = (): void => {
      if (this.unitState.SymEXT) {
         this.displayTemp = this.operationState.OutsideTemp.toString();
      }
      else {
         this.displayTemp = this.unitState.SelectedTemp.toString();

         // Show as LOW or HIGH for 18 < temp < 32
         if (this.unitState.SelectedTemp < 18) {
            this.displayTemp = 'L0'; // LOW
         }

         if (this.unitState.SelectedTemp > 32) {
            this.displayTemp = 'X1'; // HI
         }
      }
   }
}
