/**
 * Demonstration of Java Help System
 *   by calling HelpSystem.java
 * @author Tobias
 *
 */
public class HelpSystemDemo
{
    public static void main(String[] args) throws java.io.IOException
    {
        char choice, ignore;
        HelpSystem hsobj = new HelpSystem();

        for(;;)
        {
            do
            {
                hsobj.showMenu();

                choice = (char) System.in.read();

                do
                {
                    ignore = (char) System.in.read();
                } while(ignore != '\n');
            } while(!hsobj.isValid(choice));

            if(choice == 'q')
                break;

            System.out.println("\n");

            hsobj.helpOn(choice);
        }
    }
}
