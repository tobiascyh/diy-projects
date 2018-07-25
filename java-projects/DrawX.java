/**
 * Drawing X using two for loops.
 * @author Tobias Chu
 *
 */
public class DrawX
{
    public static void main(String[] args)
    {
        int limit = 5;

        for(int i = 0 ; i < limit ; i++)
        {
            for(int j = 0 ; j < limit ; j++)
            {
                if(j == i)
                {
                    System.out.print("x");
                }
                else if((limit - j - 1) == i)
                {
                    System.out.print("x");
                }
                else
                {
                    System.out.print(" ");
                }
            }

            System.out.println("");
        }
    }
}
