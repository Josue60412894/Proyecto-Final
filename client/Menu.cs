using System.Data.SQLite;


public class Menu
{
    public static void MenuInicial(string request, string ServerAddress, Int32 TCPPort, string dbLocation)
    {
       
        while (true)
        {
            // Inicio de menu principal
            Console.WriteLine("\n*******************************************************************");
            Console.WriteLine("*                 1- Menú Inicial                                 *");
            Console.WriteLine("*******************************************************************\n");
            Console.WriteLine("[1] Iniciar Sesion");
            Console.WriteLine("[2] Registrar Usuario");
            Console.WriteLine("\n*******************************************************************");
            Console.WriteLine("\nIngrese numero de opcion a elegir:");

            //Seleccion de la opcion por el usuario
            int opcion = int.Parse(Console.ReadLine());

            switch (opcion)
            {
                case 1: // Iniciar Session

                    string LoginName = "null";

                    //Inicia metodo LoginMenu e imprime el resultado de la funcion LoginMenu
                    string LoginResult = LoginMenu(ServerAddress, TCPPort, ref LoginName, dbLocation);

                    Console.WriteLine("\n*/*/" + LoginResult + "*/*/\n");

                    //Inicia metodo de UserSubMenu si el acceso es permitido
                    if (LoginResult == "acceso permitido")
                    {
                        UserSubMenu(LoginName, ServerAddress, TCPPort, dbLocation);
                    }
                    break;

                case 2: //Registrar Usuario
                    string RegistrationResult = RegisterUserMenu(ServerAddress, TCPPort);
                    Console.WriteLine(RegistrationResult);
                    break;

                default:
                    break;
            }
        }
    }

    public static string LoginMenu(string ServerAddress, Int32 TCPPort, ref string LoginName, string dbLocation)
    {
        //Metodo para loguear usuario. Retorna el string recibido del server app 

        Console.WriteLine("--> Ingrese Nombre \n");

        LoginName = Console.ReadLine(); //ingreso de nombre

        Console.WriteLine("\n--> Ingrese Password \n");

        string LoginPassword = Console.ReadLine(); //ingreso de contraseña

        // Se crea objeto de nuevo usuario
        User LoginUser = new User(LoginName, LoginPassword, "NULL", "NULL");

        // Se contruye string para enviar al server por medio del socket
        string request = $"LOGIN_USER,{LoginUser.Name},{LoginUser.Password}";

        string ServerReply = "null";

        //Se envia string al socket
        SocketClient.StartClient(request, ServerAddress, TCPPort, ref ServerReply);

        //Retorna respuesta del socket
        return ServerReply;
    }

    public static void UserSubMenu(string LoginName, string ServerAddress, Int32 TCPPort, string dbLocation)
    {
        bool RunUserSubMenu = true;

        while (RunUserSubMenu == true)
        {
            Console.WriteLine("\n*******************************************************************");
            Console.WriteLine("*                 2- Menú de Usuario                              *");
            Console.WriteLine("*******************************************************************\n");
            Console.WriteLine("[1] Registrar Orden");
            Console.WriteLine("[2] Ingresar a Sub-menu para administrar ordenes existentes");
            Console.WriteLine("[3] Cerrar Session");
            Console.WriteLine("\n*******************************************************************");
            Console.WriteLine("\nIngrese numero de opcion a elegir:");
            int opcion = int.Parse(Console.ReadLine());

            switch (opcion)
            {

                case 1: //Registro de Orden

                    string ServerReply1 = "null";

                    Console.WriteLine("--> Ingrese ID del item a Registrar \n");

                    string NewItemId = Console.ReadLine(); //ingreso de nombre

                    Console.WriteLine("\n--> Ingrese la descripcion del item a Registrar\n");

                    string NewItemDescription = Console.ReadLine(); //ingreso de contraseña

                    Console.WriteLine("\n--> Ingrese el precio del item a Registrar \n");

                    string NewPrice = Console.ReadLine(); //ingreo de contraseña

                    Console.WriteLine("\n--> Ingrese fecha de la orden a Registrar\n");

                    string NewDate = Console.ReadLine(); //ingreo de contraseña

                    //Creacion de nuevo objeto orden
                    Order NewOrder = new Order(NewItemId, NewItemDescription, NewPrice, NewDate);

                    //Escritura de la nueva orden en la Table ORDERS
                    SQLite.InsertOrderData(LoginName, NewOrder.Item_ID, NewOrder.Item_Description, NewOrder.Price, NewOrder.Date, dbLocation);

                    //Logue de evento en el servidor
                    string request_socket = $"LOG_EVENT,{LoginName},Agregar Orden {NewOrder.Item_ID} - {NewOrder.Item_Description} - {NewOrder.Price} - {NewOrder.Price}";

                    SocketClient.StartClient(request_socket, ServerAddress, TCPPort, ref ServerReply1); //envio de solicitud al server


                    break;

                case 2://Inicio del submenu para ver y eliminar ordenes
                    OrdersSubMenu(LoginName, ServerAddress, TCPPort, dbLocation);
                    break;

                case 3: //Cerrar sesion

                    string request = $"LOGOUT_USER,{LoginName}";

                    string ServerReply = "null";

                    //Escritura del evento en el servidor
                    SocketClient.StartClient(request, ServerAddress, TCPPort, ref ServerReply); //envio de solicitud al server

                    RunUserSubMenu = false;

                    break;

                default:

                    break;
            }
        }
    }

    public static string RegisterUserMenu(string ServerAddress, Int32 TCPPort)

    {
        //Metodo para registrar usuario. Retorna el string recibido del server app 

        Console.WriteLine("--> Ingrese Nombre a Registrar \n");

        string NewName = Console.ReadLine(); //ingreso de nombre

        Console.WriteLine("\n--> Ingrese Password a Registrar\n");

        string NewPassword = Console.ReadLine(); //ingreso de contraseña

        Console.WriteLine("\n--> Ingrese Teléfono a Registrar \n");

        string NewPhone = Console.ReadLine(); //ingreo de contraseña

        Console.WriteLine("\n--> Ingrese ID a Registrar\n");

        string NewID = Console.ReadLine(); //ingreo de contraseña

        User NewUser = new User(NewName, NewPassword, NewPhone, NewID); // se crea nuevo objeto de NewUser

        string request = $"ADD_USER,{NewUser.Name},{NewUser.Password},{NewUser.Phone},{NewUser.ID}";

        string ServerReply = "null";

        SocketClient.StartClient(request, ServerAddress, TCPPort, ref ServerReply); //envio de solicitud al server

        return ServerReply;
    }

    public static void OrdersSubMenu(string LoginName, string ServerAddress, Int32 TCPPort, string dbLocation)
    {

        SQLiteTableDataRetriever dataRetriever = new SQLiteTableDataRetriever();

        LinkedList<string> tableData = dataRetriever.RetrieveTableData(LoginName, dbLocation);

        while (true)
        {
            Console.WriteLine("\n*******************************************************************");
            Console.WriteLine("*                 3- Menú de Ordenes                              *");
            Console.WriteLine("*******************************************************************\n");
            Console.WriteLine("[1] Mostrar todas los ID de ordenes");
            Console.WriteLine("[2] Mostrar los detalles especificos de una orden");
            Console.WriteLine("[3] Eliminar una orden");
            Console.WriteLine("[4] Volver al menu anterior");
            Console.WriteLine("\n*******************************************************************");
            Console.WriteLine("\nIngrese numero de opcion a elegir:");
            int opcion = int.Parse(Console.ReadLine());


            switch (opcion)
            {
                case 1: //Mostrar todas los ID de ordenes
                    //Guardar lista de todos los item de tabla ORDERS en una lista enlazada
                    tableData = dataRetriever.RetrieveTableData(LoginName, dbLocation);

                    int counter = 3;
                    int printFrequency = 5;

                    Console.WriteLine("\nLa lista de orders ID es la siguiente \n");
                    //Imprime solo los valores en cada 4ta posicion (User, Order ID*, DESCRIPCION, PRICE, DATE)
                    foreach (string value in tableData)
                    {
                        counter++;

                        if (counter % printFrequency == 0)
                        {
                            Console.WriteLine(value);
                        }
                    }

                    //Registro del evento en el servidor
                    string ServerReply1 = "null";

                    string request_socket = $"LOG_EVENT,{LoginName}, Se mostraron los IDs de todas las ordenes";

                    SocketClient.StartClient(request_socket, ServerAddress, TCPPort, ref ServerReply1); //envio de solicitud al server

                    break;

                case 2: //Mostrar los detalles especificos de una orden

                    Console.WriteLine("\n--> Ingrese el order ID a mostrar\n");

                    string ServerReply2 = "null";

                    string OrderIdToShow = Console.ReadLine(); //ingreso de order ID

                    //Logue evento en el servidor

                    string request_socket1 = $"LOG_EVENT,{LoginName}, Se mostraron los detalles de la orden {OrderIdToShow}";

                    SocketClient.StartClient(request_socket1, ServerAddress, TCPPort, ref ServerReply2); //envio de solicitud al server

                    //Actualiza la lista con las ordenes actuales en la base de datos

                    tableData = dataRetriever.RetrieveTableData(LoginName, dbLocation);

                    bool found = false;
                    int matchCount = 0;
                    int itemsToPrint = 3;


                    //Imprime los siguientes 4 valores del la lista luego de encontrar el ID

                    foreach (string item in tableData)
                    {
                        if (found)
                        {
                            if (matchCount == 2)
                            {
                                Console.WriteLine("DATE = " + item);
                                matchCount++;
                            }
                            if (matchCount == 1)
                            {
                                Console.WriteLine("PRICE = " + item);
                                matchCount++;
                            }
                            if (matchCount == 0)
                            {
                                Console.WriteLine("ITEM DESCRIPTION = " + item);
                                matchCount++;
                            }
                            if (matchCount >= itemsToPrint)
                            {
                                break;
                            }
                        }
                        else if (item == OrderIdToShow)
                        {
                            Console.WriteLine("\nORDER ID = " + item);
                            found = true;
                        }
                    }

                    break;

                case 3: //Eliminar un Order ID

                    Console.WriteLine("\n--> Ingrese el order ID a eliminar\n");

                    string OrderIdToDelete = Console.ReadLine(); //ingreso de contraseña

                    //Eliminacion de la Order en la tabl ORDERS de SQLite
                    SQLite.DeleteOrderID(OrderIdToDelete, dbLocation);

                    string ServerReply3 = "null";

                    //Registro de evento en el servidor 
                    string request_socket2 = $"LOG_EVENT,{LoginName}, Se elimino la orden {OrderIdToDelete}";

                    SocketClient.StartClient(request_socket2, ServerAddress, TCPPort, ref ServerReply3); //envio de solicitud al server

                    break;

                case 4://retornar el menu anterior
                    return;
                    break;

                default:

                    break;
            }
        }
    }
}