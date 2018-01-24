
#include "serial.h"
#include <stdio.h>
#include <string.h>
void* open_serial_port(char* COM_PORT,char lenth){
			HANDLE h_comm;                          // Handle to the Serial port
			char  com_port_name[lenth];//"\\\\.\\COM24" Name of the Serial port(May Change) to be opened,
			BOOL  status;                          // Status of the various operations 
			DWORD no_bytes_read;                     // Bytes read by ReadFile()
			int i = 0;
			for (i = 0;i < lenth;i++){
				com_port_name[i] = COM_PORT[i];
			} 
			i = 0;
			printf("\n\n +==========================================+");
			printf("\n |    Serial Port  Reception (Win32 API)    |");
			printf("\n +==========================================+\n");
			/*---------------------------------- Opening the Serial Port -------------------------------------------*/
			
			h_comm = CreateFile( com_port_name,                  // Name of the Port to be Opened
		                        GENERIC_READ | GENERIC_WRITE, // Read/Write Access
								0,                            // No Sharing, ports cant be shared
								NULL,                         // No Security
							    OPEN_EXISTING,                // Open existing port only
		                        0,                            // Non Overlapped I/O
		                        NULL);                        // Null for Comm Devices

			if (h_comm == INVALID_HANDLE_VALUE){
				printf("\n    Error! - Port %s can't be opened\n", com_port_name);
			}else{
				printf("\n    Port %s Opened\n ", com_port_name);
            /*------------------------------- Setting the Parameters for the SerialPort ------------------------------*/
                
                DCB dcb_serial_params = { 0 };                         // Initializing DCB structure
                dcb_serial_params.DCBlength = sizeof(dcb_serial_params);

                status = GetCommState(h_comm, &dcb_serial_params);      //retreives  the current settings

                if (status == FALSE){
                    printf("\n    Error! in GetCommState()");
                }else{
                    dcb_serial_params.BaudRate = CBR_115200;      // Setting BaudRate = 9600
                    dcb_serial_params.ByteSize = 8;             // Setting ByteSize = 8
                    dcb_serial_params.StopBits = ONESTOPBIT;    // Setting StopBits = 1
                    dcb_serial_params.Parity = NOPARITY;        // Setting Parity = None 

                    status = SetCommState(h_comm, &dcb_serial_params);  //Configuring the port according to settings in DCB 

                    if (status == FALSE){
                        printf("\n    Error! in Setting DCB Structure");
                    }else{ //If Successfull display the contents of the DCB Structure
                        printf("\n\n    Setting DCB Structure Successfull\n");
                        printf("\n       Baudrate = %d", dcb_serial_params.BaudRate);
                        printf("\n       ByteSize = %d", dcb_serial_params.ByteSize);
                        printf("\n       StopBits = %d", dcb_serial_params.StopBits);
                        printf("\n       Parity   = %d", dcb_serial_params.Parity);
                        /*------------------------------------ Setting Timeouts --------------------------------------------------*/
                        COMMTIMEOUTS timeouts = { 0 };
                        timeouts.ReadIntervalTimeout         = 50;
                        timeouts.ReadTotalTimeoutConstant    = 50;
                        timeouts.ReadTotalTimeoutMultiplier  = 10;
                        timeouts.WriteTotalTimeoutConstant   = 50;
                        timeouts.WriteTotalTimeoutMultiplier = 10;
                        if (SetCommTimeouts(h_comm, &timeouts) == FALSE){
                            printf("\n\n    Error! in Setting Time Outs");
                        }else{
                            printf("\n\n    Setting Serial Port Timeouts Successfull");
                            status = SetCommMask(h_comm, EV_RXCHAR); //Configure Windows to Monitor the serial device for Character Reception
                    
                            if (status == FALSE){
                                printf("\n\n    Error! in Setting CommMask");
                            }else{
                                printf("\n\n    Setting CommMask successfull");
                                return h_comm;
                            }
                        }
                        /*------------------------------------ Setting Receive Mask ----------------------------------------------*/
                    }
                }
			}
			return NULL;
}

char read_from_serial_port(char* buff_read,HANDLE h_comm){
	DWORD dw_event_mask;                     // Event mask to trigger
    char  temp_char;                        // Temperory Character
    char  serial_buffer[256];               // Buffer Containing Rxed Data
    DWORD no_bytes_read;                     // Bytes read by ReadFile()
    BOOL  status;                          // Status of the various operations
    char lenth;
    /*------------------------------------ Setting WaitComm() Event   ----------------------------------------*/

	printf("\n\n    Waiting for Data Reception");

	status = WaitCommEvent(h_comm, &dw_event_mask, NULL); //Wait for the character to be received

	/*-------------------------- Program will Wait here till a Character is received ------------------------*/				

	if (status == FALSE){
	   printf("\n    Error! in Setting WaitCommEvent()");
	}else{ //If  WaitCommEvent()==True Read the RXed data using ReadFile();
		printf("\n\n    Characters Received");
        int i = 0;
	    do{
	        status = ReadFile(h_comm, &temp_char, sizeof(temp_char), &no_bytes_read, NULL);
	        serial_buffer[i] = temp_char;
	        i++;
	    }while (no_bytes_read > 0 && i < 256);
        lenth = i-1;
        int j =0;
        for (j = 0; j < i-1; j++){      // j < i-1 to remove the dupliated last character
             buff_read[j] = serial_buffer[j];
        }
	}	

	
	printf("\n +==========================================+\n");
    return lenth;
//	_getch();
}
char write_to_serial_port(char* buff_write,char lenth,HANDLE h_comm){
        DWORD  dNoOFBytestoWrite;              // No of bytes to write into the port
        DWORD  dNoOfBytesWritten = 0;          // No of bytes written to the port
        BOOL status;
        char temp_buff[lenth];
        dNoOFBytestoWrite = lenth; // Calculating the no of bytes to write into the port
        for(int i = 0;i<lenth;i++){
            temp_buff[i] = buff_write[i];
        }
        status = WriteFile(h_comm,               // Handle to the Serialport
                           temp_buff,            // Data to be written to the port 
                           dNoOFBytestoWrite,   // No of bytes to write into the port
                           &dNoOfBytesWritten,  // No of bytes written to the port
                           NULL);
        if (status == TRUE){
            printf("\n\n    %s - Written to com port", temp_buff);
        }else{
            printf("\n\n   Error %d in Writing to Serial Port",GetLastError());
        }

        printf("\n ==========================================\n");
}
char close_serial_port(HANDLE h_comm){
	printf("\n close serial port\n");
    CloseHandle(h_comm);//Closing the Serial Port
}
