package com.stt0504.Console.BankActions;

import com.stt0504.Console.Action;
import com.stt0504.User.User;
import java.util.Objects;
import java.util.Scanner;

/**
 * The RegistrationAction class represents an action to register a new user in the bank system.
 * It extends the Action class and prompts the user to enter their registration details.
 */
public class RegistrationAction extends Action {

    /**
     * Constructor for RegistrationAction class.
     * @param name The name of the registration action.
     */
    public RegistrationAction(String name) {
        super(name);
    }

    /**
     * Runs the action by prompting the user to enter their registration details and registering them.
     * Sets the registered user to the data manager of the next action and executes it.
     */
    public void Run() {
        Scanner sc = new Scanner(System.in);

        // Prompt the user to enter their name
        System.out.println("Enter name: ");
        String name = sc.nextLine();

        // Prompt the user to enter their surname
        System.out.println("Enter surname: ");
        String surname = sc.nextLine();

        // Prompt the user to enter their address
        System.out.println("Enter address: ");
        String address = sc.nextLine();

        // Prompt the user to enter their passport number
        System.out.println("Enter the passport number: ");
        String passportNumber = sc.nextLine();

        // Prompt the user to enter their desired login
        System.out.println("Enter the login: ");
        String login = sc.nextLine();

        // Prompt the user to enter their desired password
        System.out.println("Enter the password: ");
        String password = sc.nextLine();

        // Prompt the user to confirm their password
        System.out.println("Enter the password again: ");
        String password2 = sc.nextLine();

        // Check if the passwords match
        if (Objects.equals(password, password2)) {
            // If passwords match, add the new user to the bank system
            manager.bank.AddUser(new User.Builder()
                    .setName(name)
                    .setSurname(surname)
                    .setAddress(address)
                    .setPassportNumber(passportNumber)
                    .setLogin(login)
                    .setPassword(password)
                    .build());
        }

        // Set the registered user to the data manager of the next action and execute it
        next.manager = manager;
        next.Run();
    }
}
