import { Component, OnInit, ViewChild, ElementRef, AfterViewInit } from '@angular/core';
import { SignalRService } from './services/signalR.services';

@Component({
   selector: 'app-root',
   templateUrl: './app.component.html',
   styleUrls: ['./app.component.css'],
})
export class AppComponent implements OnInit, AfterViewInit {
   // Variables
   title: string = 'A/C Electronic Unit';

   // Scroll messages frame
   @ViewChild('messagesframe', { static: false }) messagesFrame: ElementRef;
   private messagesContainer: any;

   constructor(public signalRService: SignalRService) {
      signalRService.observable$.subscribe(message => {
         console.log('AppComponent <subscribe>: ' + message);
         this.scrollMessagesToBottom();
      });
   }

   ngOnInit() {
      console.log('AppComponent <OnInit>');

      console.log('|-Setting SignalR client');
      this.signalRService.startConnection();
      this.signalRService.addUnitStateListener();
      this.signalRService.addOperationStateListener();
   }

   ngAfterViewInit() {
      this.messagesContainer = this.messagesFrame.nativeElement;
   }

   private scrollMessagesToBottom(): void {
      const thres = 185;   // 185 = 210 <DIV Height> - 25 <Message Height>
      const pos = this.messagesContainer.scrollTop + this.messagesContainer.offsetHeight;
      const height = this.messagesContainer.scrollHeight;
      if (pos > height - thres) {
         this.messagesContainer.scroll({
            top: height + thres,
            left: 0,
            behavior: 'smooth'
         });
      }

      // Limit messages to 25 items
      if (this.signalRService.messages.length >= 25) {
         this.signalRService.messages.splice(0, 1);
      }
   }
}
