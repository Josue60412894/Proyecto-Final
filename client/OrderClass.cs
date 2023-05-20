
public struct Order
{
    public string Item_ID;
    public string Item_Description;
    public string Price;
    public string Date;

    // Constructor
    public Order(string x1, string x2, string x3, string x4)
    {
        Item_ID = x1;
        Item_Description = x2;
        Price = x3;
        Date = x4;
    }
}