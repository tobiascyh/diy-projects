/**
 * Practice ? : conditional operator
 * @author Tobias
 *
 */
public class ConditionalOp
{
    private String trueState()
    {
        return "This is true.";
    }

    private String falseState()
    {
        return "This is false.";
    }

    public static void main(String[] args)
    {
        Practice2c test = new Practice2c();
        boolean bool;
        String str;

        bool = false;

        str = bool ? test.trueState() : test.falseState();

        System.out.println(str);

        if(bool)
            str = test.trueState();
        else
            str = test.falseState();

        System.out.println(str);
    }
}
