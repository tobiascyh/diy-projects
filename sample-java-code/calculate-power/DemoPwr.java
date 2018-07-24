
public class DemoPwr
{
    public static void main(String[] args)
    {
        CalcPwr x = new CalcPwr(4.0, 2);
        CalcPwr y = new CalcPwr(2.5, 1);
        CalcPwr z = new CalcPwr(5.7, 0);
        
        System.out.println(x.b + " raised to the " + x.e +
                            " power is " + x.get_pwr());
        System.out.println(y.b + " raised to the " + y.e +
                            " power is " + y.get_pwr());
        System.out.println(z.b + " raised to the " + z.e +
                            " power is " + z.get_pwr());
    }
}
