package com.stt0504.Commands;

import com.stt0504.*;

import java.util.List;
import java.util.Scanner;

public class ShowOwnerInfoCommand implements Command {
    private final OwnerService ownerService;
    private final CatService catService;

    public String getName() {
        return "Show owner information";
    }

    public ShowOwnerInfoCommand(OwnerService ownerService, CatService catService) {
        this.ownerService = ownerService;
        this.catService = catService;
    }

    @Override
    public void execute() {
        Scanner scanner = new Scanner(System.in);

        System.out.println();
        System.out.print("Enter the owner's ID: ");
        long id = Long.parseLong(scanner.nextLine());

        OwnerDTO owner = ownerService.getOwnerById(id);
        if (owner != null) {
            System.out.println("Owner information: ");
            System.out.println("Name: " + owner.getName());
            System.out.println("Birth date: " + owner.getBirthDate());
            List<CatDTO> cats = catService.getCats(owner);
            if (cats != null && !cats.isEmpty()) {
                System.out.println("List of cats: ");
                for (CatDTO cat: cats) {
                    System.out.println("• " + cat.getName());
                }
            } else {
                System.out.println("This owner doesn't have any cat yet.");
            }
            System.out.println();
        } else {
            System.out.println("Owner with the specified ID not found.");
        }
        System.out.println();
    }
}