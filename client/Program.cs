using System.Net;
using System.Net.Sockets;
using System.Text;

class Program
{
    static void Main(String[] args)

    {
        // Parametros de para comunicacion de socket
        string request = "hello";
        string ServerAddress = "127.0.0.1";
        Int32 TCPPort = 6336;
        
        //Ubicacion de la base de datos SQL
        string dbLocation = "Data Source=C:\\Users\\josue\\OneDrive\\Documentos\\Curso-Cenfotec\\Trabajos\\FinalProject\\server\\OrderHandlerUC.db;Version=3;";


        // Inicia la funcion de Menu
        Menu.MenuInicial(request, ServerAddress, TCPPort, dbLocation);


    }

}







