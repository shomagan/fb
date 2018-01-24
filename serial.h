#include <Windows.h>
struct com_str{
	HANDLE h_comm;                          // Handle to the Serial port
	char com_port_name[32];//"\\\\.\\COM24" Name of the Serial port(May Change) to be opened,
	char lenth;
	BOOL  status;                          // Status of the various operations 
	DWORD dw_event_mask;                     // Event mask to trigger
	char  temp_char;                        // Temperory Character
	char  serial_buffer[256];               // Buffer Containing Rxed Data
	DWORD no_bytes_read;                     // Bytes read by ReadFile()
	DCB dcb_serial_params;
	COMMTIMEOUTS timeouts;

};
void* open_serial_port(char* COM_PORT,char lenth);
char read_from_serial_port(char* buff_read,HANDLE h_comm);
char write_to_serial_port(char* buff_write,char lenth,HANDLE h_comm);
char close_serial_port(HANDLE h_comm);
