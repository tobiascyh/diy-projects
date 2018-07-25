/**
 * Truth table for the logical operators using 1 and 0.
 * @author Tobias Chu
 *
 */
public class TruthTable2
{
    private static String printBoolean(boolean pq)
    {
        return pq ? "1" : "0";
    }

    public static void main(String[] args)
    {
        boolean p, q;

        System.out.println("P\tQ\tAND\tOR\tXOR\tNOT");

        p = true; q = true;
        System.out.print(printBoolean(p) + "\t" + printBoolean(q) + "\t");
        System.out.print(printBoolean(p&q) + "\t" + printBoolean(p|q) + "\t");
        System.out.println(printBoolean(p^q) + "\t" + printBoolean(!p));

        p = true; q = false;
        System.out.print(printBoolean(p) + "\t" + printBoolean(q) + "\t");
        System.out.print(printBoolean(p&q) + "\t" + printBoolean(p|q) + "\t");
        System.out.println(printBoolean(p^q) + "\t" + printBoolean(!p));

        p = false; q = true;
        System.out.print(printBoolean(p) + "\t" + printBoolean(q) + "\t");
        System.out.print(printBoolean(p&q) + "\t" + printBoolean(p|q) + "\t");
        System.out.println(printBoolean(p^q) + "\t" + printBoolean(!p));

        p = false; q = false;
        System.out.print(printBoolean(p) + "\t" + printBoolean(q) + "\t");
        System.out.print(printBoolean(p&q) + "\t" + printBoolean(p|q) + "\t");
        System.out.println(printBoolean(p^q) + "\t" + printBoolean(!p));
    }
}
