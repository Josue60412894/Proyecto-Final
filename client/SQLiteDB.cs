using System.Data.SQLite;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public class SQLite
{
    public static void InsertOrderData(string LoginName, string Item_ID, string Item_Description, string Price, string Date, string dbLocation)
    {
        //Apertura de la base de datos
        using (SQLiteConnection connection = new SQLiteConnection(dbLocation))
        {
            connection.Open();

            //Crecion del string SQlite
            string insertQuery = $"INSERT INTO {"ORDERS"} ({"USER_NAME"}, {"ITEM_ID"}, {"ITEM_DESCRIPTION"}, {"PRICE"}, {"DATE"}) VALUES (@loginName, @Value1, @Value2, @Value3, @Value4)";

            //Ejecucion del string 
            using (SQLiteCommand command = new SQLiteCommand(insertQuery, connection))
            {
                command.Parameters.AddWithValue("@loginName", LoginName);
                command.Parameters.AddWithValue("@Value1", Item_ID);
                command.Parameters.AddWithValue("@Value2", Item_Description);
                command.Parameters.AddWithValue("@Value3", Price);
                command.Parameters.AddWithValue("@Value4", Date);
                command.ExecuteNonQuery();
            }
        }
    }

    public static void DeleteOrderID(string OrderID, string dbLocation)
    {
        using (SQLiteConnection connection = new SQLiteConnection(dbLocation))
        {
            //Apertura de la base de datos
            connection.Open();

            //Crecion del string SQlite
            string deleteQuery = $"DELETE FROM ORDERS WHERE ITEM_ID = @RowId";

            //Ejecucion del string 
            using (SQLiteCommand command = new SQLiteCommand(deleteQuery, connection))
            {
                command.Parameters.AddWithValue("@RowId", OrderID);
                command.ExecuteNonQuery();
            }
        }
    }
}



public class SQLiteTableDataRetriever
{
    //Metodo para extraer todas las ordenes de la base de datos y almacenarlo en una lista enlazada
    public LinkedList<string> RetrieveTableData(string Name, string dbLocation)
    {
        LinkedList<string> tableData = new LinkedList<string>();

        using (SQLiteConnection connection = new SQLiteConnection(dbLocation))
        {
            connection.Open();

            string query = "SELECT * FROM ORDERS WHERE USER_NAME = '" + Name + "';";

            using (SQLiteCommand command = new SQLiteCommand(query, connection))
            {
                using (SQLiteDataReader reader = command.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        // Lectura de cada columna 1-USERNAME, 2-ITEM-ID, 3-Description, 4-PRICE, 5-DATE
                        string value = reader.GetString(0);
                        tableData.AddLast(value);
                        value = reader.GetString(1);
                        tableData.AddLast(value);
                        value = reader.GetString(2);
                        tableData.AddLast(value);
                        value = reader.GetString(3);
                        tableData.AddLast(value);
                        value = reader.GetString(4);
                        tableData.AddLast(value);
                    }
                }
            }
        }

        return tableData;
    }
}
