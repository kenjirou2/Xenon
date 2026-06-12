#include "menu.h"

void menu(void)
{
	printf(PURPLE
        "\n.----------------.  .----------------.  .----------------.  .----------------.  .----------------.\n"
        "| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |\n"
        "| |  ____  ____  | || |  _________   | || | ____  _____  | || |     ____     | || | ____  _____  | |\n"
        "| | |_  _||_  _| | || | |_   ___  |  | || ||_   \\|_   _| | || |   .'    `.   | || ||_   \\|_   _| | |\n"
        "| |   \\ \\  / /   | || |   | |_  \\_|  | || |  |   \\ | |   | || |  /  .--.  \\  | || |  |   \\ | |   | |\n"
        "| |    > `' <    | || |   |  _|  _   | || |  | |\\ \\| |   | || |  | |    | |  | || |  | |\\ \\| |   | |\n"
        "| |  _/ /'`\\ \\_  | || |  _| |___/ |  | || | _| |_\\   |_  | || |  \\  `--'  /  | || | _| |_\\   |_  | |\n"
        "| | |____||____| | || | |_________|  | || ||_____\\____| | || |   `.____.'   | || ||_____\\____| | |\n"
        "| |              | || |              | || |              | || |              | || |              | |\n"
        "| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |\n"
        " '----------------'  '----------------'  '----------------'  '----------------'  '----------------' \n"
    BLACK);
    return;
}

void help_menu(void)
{
    printf(WHITE"\nXenon v3.1.5");
    printf("\nUsage: Xenon [options] [arguments]\n");
    printf("\nSOCKET TYPES:");
    printf("\t\n -TCP : Transmission Control Protocol");
    printf("\t\n -UDP : User Datagram Protocol");
    printf("\t\n -TLS : Transport Layer Security");
    printf("\n\nFAMILY:");
    printf("\t\n -ipv4 : 4 byte internet protocol address");
    printf("\t\n - ipv6 : 4 byte internet protocol address");
    printf("\n\nOPTIONS:");
    printf("\t\n -v : Version");
    printf("\t\n -v? : Http status code");
    printf("\t\n -h/ -help / ? : Help");
    printf("\t\n -s : select [arguments]");
    printf("\t\n -conn : [port]");
    printf("\t\n         Accept connection from a random node\n");
    printf("\t\n -sconn : [family] [type] [port] [address]");
    printf("\t\n          Accept connection from specific node\n");
    printf("\t\n -mconn : [port]");
    printf("\t\n          Get a list of all nodes connected to your device you can use (-select [ID]) to accept connection"BLACK);
    return;
}

void login(void)
{

    menu();

    char username[100];
    uint32_t password;

    printf(WHITE"Enter Username : ");
    if (scanf("%99s", username) != 1 || username[0] == '\0')
    {
        fprintf(stderr, RED "\nUsername cannot be empty" BLACK);
        return;
    }

    printf(WHITE"Enter Password : ");
    if (scanf("%u", &password) != 1 || password == 0)
    {
        fprintf(stderr, RED "\nInvalid password" BLACK);
        return;
    }

}