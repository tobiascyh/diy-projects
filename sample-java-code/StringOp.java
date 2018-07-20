import java.util.Scanner;
import java.util.StringTokenizer;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class StringOp
{
    private String storedString;
    private String ignoredString;
    private String delimiter = " ";
    private StringTokenizer strToken;
    private Scanner keyboard = new Scanner(System.in);

    public int showMenu()
    {
        System.out.println("1) Input string");
        System.out.println("2) Print string");
        System.out.println("3) Reverse the string");
        System.out.println("4) Tokenize string");
        System.out.println("5) Count spaces in the string");
        System.out.println("6) Check for a number in the string");
        System.out.println("7) Count vowels");
        System.out.println("8) Count consonants");
        System.out.println("9) Exit program");

        System.out.print("Please choose an option: ");
        return keyboard.nextInt();
    }

    public void select(int input)
    {
        if(input >= 1 && input <= 9)
        {
            if(storedString != null || input == 1 || input == 9)
            {
                switch(input)
                {
                case 1:
                    setString();
                    break;
                case 2:
                    printString();
                    break;
                case 3:
                    reverseString();
                    break;
                case 4:
                    tokenizeString();
                    break;
                case 5:
                    countSpaces();
                    break;
                case 6:
                    checkNumber();
                    break;
                case 7:
                    countVowels();
                    break;
                case 8:
                    countConsonants();
                    break;
                case 9:
                    System.out.println("Program ended.");
                    break;
                }
            }
            else
            {
                System.out.println("No string entered. Please enter a string first.");
            }
        }
        else
        {
            System.out.println(input + " is not valid. Please enter a valid option.");
        }

        System.out.println();
    }

    public void setString()
    {
        ignoredString = keyboard.nextLine();
        System.out.println("Enter a string:");
        storedString = keyboard.nextLine();
        System.out.println("String entered.");
    }

    public void printString()
    {
        System.out.println("String: " + storedString);
    }

    public void reverseString()
    {
        int i, j = 0;
        char[] reverse = new char[storedString.length()];
        char[] temp = storedString.toCharArray();

        for(i = temp.length - 1 ; i >= 0 ; i-- , j++)
        {
            reverse[j] = temp[i];
        }

        storedString = String.valueOf(reverse);
        System.out.println("Reversed string: " + storedString);
    }

    public void tokenizeString()
    {
        strToken = new StringTokenizer(storedString, delimiter);
        while(strToken.hasMoreTokens())
        {
            System.out.println(strToken.nextToken());
        }
    }

    public void countSpaces()
    {
        int numSpace = 0;
        char[] temp = storedString.toCharArray();

        for(int i = 0 ; i < temp.length ; i++)
        {
            if(Character.isWhitespace(temp[i]))
            {
                numSpace++;
            }
        }

        System.out.println("Number of spaces = " + numSpace);
    }

    public void checkNumber()
    {
        Pattern checkInt = Pattern.compile("\\d+");
        Matcher findMatch = checkInt.matcher(storedString);

        if(findMatch.find())
        {
            System.out.println("True.");
        }
        else
        {
            System.out.println("False.");
        }
    }

    public void countVowels()
    {
        int numVowel = 0;

        //Pattern checkInt = Pattern.compile("[a-zA-Z&&[^aeiouAEIOU]]+");
        Pattern checkInt = Pattern.compile("[\\w&&[aeiouAEIOU]]+");
        Matcher findMatch = checkInt.matcher(storedString);

        while(!findMatch.hitEnd())
        {
            if(findMatch.find())
            {
                numVowel++;
            }
        }

        System.out.println("String: " + storedString);
        System.out.println("Number of vowels = " + numVowel);
    }

    public void countConsonants()
    {
        int numConsonant = 0;

        Pattern checkInt = Pattern.compile("[\\w&&[^aeiouAEIOU0-9]]+");
        Matcher findMatch = checkInt.matcher(storedString);

        while(!findMatch.hitEnd())
        {
            if(findMatch.find())
            {
                numConsonant++;
            }
        }

        System.out.println("String: " + storedString);
        System.out.println("Number of consonants = " + numConsonant);
    }

    /*
     * Main function
     */
    public static void main(String[] args)
    {
        StringOp application = new StringOp();
        int input;

        do
        {
            input = application.showMenu();
            application.select(input);

        } while (input != 9);
    }
}
