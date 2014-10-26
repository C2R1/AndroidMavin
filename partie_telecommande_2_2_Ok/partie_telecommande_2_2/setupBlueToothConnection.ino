void setupBlueToothConnection()
{
  blueToothSerial.begin(38400); //Set BluetoothBee BaudRate to default baud rate 38400
  blueToothSerial.print("\r\n+STWMOD=1\r\n");//set the bluetooth work in master mode
  blueToothSerial.print("\r\n+STNA=SeeedBTMaster\r\n");//set the bluetooth name as "SeeedBTMaster"
  blueToothSerial.print("\r\n+STAUTO=0\r\n");// Auto-connection is forbidden here
  delay(2000); // This delay is required.
  blueToothSerial.flush();
  blueToothSerial.print("\r\n+INQ=1\r\n");//make the master inquire
  Serial.println("Master is inquiring!");
 
  delay(2000); // This delay is required.
    
  //find the target slave
  char recvChar;
  
  while(1){
    
    if(blueToothSerial.available()){
      recvChar = blueToothSerial.read();
      recvBuf += recvChar;
      nameIndex = recvBuf.indexOf(slaveName);//get the position of slave name
      
      //nameIndex -= 1;//decrease the ';' in front of the slave name, to get the position of the end of the slave address
      if ( nameIndex != -1 ){
        //Serial.print(recvBuf);
 	addrIndex = (recvBuf.indexOf(retSymb,(nameIndex - retSymb.length()- 18) ) + retSymb.length());//get the start position of slave address	 		
 	slaveAddr = recvBuf.substring(addrIndex, nameIndex);//get the string of slave address 	
 Serial.println("Master is ne trouve rien");		
 	break;
      }
    }
  }
  //form the full connection command
  connectCmd += slaveAddr;
  connectCmd += "\r\n";
  int connectOK = 0;
  Serial.print("Connecting to slave:");
  Serial.print(slaveAddr);
  Serial.println(slaveName);
  //connecting the slave till they are connected
  do{
    blueToothSerial.print(connectCmd);//send connection command
    recvBuf = "";
    while(1){
      if(blueToothSerial.available()){
        recvChar = blueToothSerial.read();
 	recvBuf += recvChar;
 	if(recvBuf.indexOf("CONNECT:OK") != -1){
          connectOK = 1;
 	  Serial.println("Connected!");
 	  blueToothSerial.print("Connected!");
          break;
 	}else if(recvBuf.indexOf("CONNECT:FAIL") != -1){
 	  Serial.println("Connect again!");
 	  break;
 	}
      }
    }
  }while(0 == connectOK);
}
