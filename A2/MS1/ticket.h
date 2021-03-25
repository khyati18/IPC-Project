
struct Message
{
	char account_type;
	char user_name[31];
	char message_details[151];
};

struct Ticket
{
	int ticket_number;
	int customer_account_number;
	int ticket_status;
	char subject_line[31];
	int message_counter;

	struct Message msg_array[21];
};