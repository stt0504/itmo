package com.stt0504;

import com.stt0504.Commands.*;

import java.util.List;
import java.util.Scanner;

public class ConsoleController {
    private final List<Command> commands;

    public ConsoleController(List<Command> commands) {
        this.commands = commands;
    }

    public void start() {
        while (true) {
            printMenu();
            Scanner scanner = new Scanner(System.in);
            int choice = scanner.nextInt();
            scanner.nextLine();

            if (choice == commands.size()) {
                break;
            }

            executeCommand(choice);
        }
    }

    private void printMenu() {
        System.out.println("Choose an action:");
        for (int i = 0; i < commands.size(); i++) {
            Command command = commands.get(i);
            System.out.println((i + 1) + ". " + command.getName());
        }
        System.out.print("Enter the action number: ");
    }

    private void executeCommand(int choice) {
        if (choice >= 1 && choice <= commands.size()) {
            commands.get(choice - 1).execute();
        } else {
            System.out.println("Incorrect input, please try again");
        }
    }
}
