/* ФБ "Синхронизатор времени" */

typedef struct {
	Register_type Enable;     // "1" синхронизирует время
	Register_type Time;       // Время в формате UNIX для синхронизации
} fb00044_IN_type;
