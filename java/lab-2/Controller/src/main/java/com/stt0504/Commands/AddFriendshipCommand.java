package com.stt0504.Commands;

import com.stt0504.CatService;

import java.util.Scanner;

public class AddFriendshipCommand implements Command {
    private final CatService catService;

    public String getName() {
        return "Add friendship between cats";
    }

    public AddFriendshipCommand(CatService catService) {
        this.catService = catService;
    }

    @Override
    public void execute() {
        Scanner scanner = new Scanner(System.in);

        System.out.println();
        System.out.print("Enter the first cat's ID: ");
        long id1 = Long.parseLong(scanner.nextLine());

        System.out.print("Enter the second cat's ID: ");
        long id2 = Long.parseLong(scanner.nextLine());

        catService.addFriendship(id1, id2);
        System.out.println();
    }
}