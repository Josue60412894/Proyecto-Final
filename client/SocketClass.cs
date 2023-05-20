using System.Net;
using System.Net.Sockets;
using System.Text;

// Client app is the one sending messages to a Server/listener.
// Both listener and client can send messages back and forth once a
// communication is established. TEST TEST
public class SocketClient
{

    public static void StartClient(string Request, string ServerIpAddress, Int32 PortNumber, ref string ReturnString)
    {
        byte[] bytes = new byte[1024];

        try
        {
            // Get the Name of HOST  
            string hostName = ServerIpAddress;
            //Console.WriteLine(hostName);

            // Get the IP from GetHostByName method of dns class
            IPAddress ipAddress = Dns.GetHostByName(hostName).AddressList[0];
           // Console.WriteLine("IP Address is : " + ipAddress.ToString());
            IPEndPoint remoteEP = new IPEndPoint(ipAddress, PortNumber);

            // Create a TCP/IP  socket.
            Socket sender = new Socket(ipAddress.AddressFamily,
                SocketType.Stream, ProtocolType.Tcp);

            // Connect the socket to the remote endpoint. Catch any errors.
            try
            {
                // Connect to Remote EndPoint
                sender.Connect(remoteEP);

                //Console.WriteLine("Socket connected to {0}", sender.RemoteEndPoint.ToString());

                // Encode the data string into a byte array.
                byte[] msg = Encoding.ASCII.GetBytes(Request);

                // Send the data through the socket.
                int bytesSent = sender.Send(msg);

                // Receive the response from the remote device.
                int bytesRec = sender.Receive(bytes);
                //Console.WriteLine("Echoed test = {0}", Encoding.ASCII.GetString(bytes, 0, bytesRec));
                string ReturnString1;
                
                ReturnString1 = Encoding.ASCII.GetString(bytes, 0, bytesRec); // return received string from server
               
                ReturnString = ReturnString1;

                // Release the socket.
                sender.Shutdown(SocketShutdown.Both);

                sender.Close();

                

            }
            catch (ArgumentNullException ane)
            {
                Console.WriteLine("ArgumentNullException : {0}", ane.ToString());
                

            }
            catch (SocketException se)
            {
                Console.WriteLine("SocketException : {0}", se.ToString());
                 

            }
            catch (Exception e)
            {
                Console.WriteLine("Unexpected exception : {0}", e.ToString());
                

            }

        }
        catch (Exception e)
        {
            Console.WriteLine(e.ToString());
        }
    }
}
