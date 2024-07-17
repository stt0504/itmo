package com.stt0504.Commands;

import com.stt0504.CatDTO;
import com.stt0504.CatService;

import java.util.List;
import java.util.Scanner;

public class ShowCatInfoCommand implements Command {
    private final CatService catService;

    public String getName() {
        return "Show cat information by id";
    }

    public ShowCatInfoCommand(CatService catService) {
        this.catService = catService;
    }

    @Override
    public void execute() {
        Scanner scanner = new Scanner(System.in);

        System.out.println();
        System.out.print("Enter the cat's ID: ");
        long id = Long.parseLong(scanner.nextLine());

        CatDTO cat = catService.getCatById(id);
        if (cat != null) {
            System.out.println("Cat information: ");
            showCatInfo(cat);
        } else {
            System.out.println("Cat with the specified ID not found.");
        }
        System.out.println();
    }

    public void showCatInfo(CatDTO cat) {
        ShowCatInfo(cat, catService);
    }

    static void ShowCatInfo(CatDTO cat, CatService catService) {
        System.out.println();
        System.out.println("Name: " + cat.getName());
        System.out.println("Birth date: " + cat.getBirthDate());
        System.out.println("Breed: " + cat.getBreed());
        System.out.println("Color: " + cat.getColor());
        System.out.println("Owner's ID: " + cat.getOwnerId());

        List<CatDTO> friends = catService.getFriends(cat);
        if (friends != null && !friends.isEmpty()) {
            System.out.println("List of friends:");
            for (CatDTO friend: friends) {
                System.out.println("• " + friend.getName());
            }
        } else {
            System.out.println("This cat doesn't have any friends yet.");
        }
        System.out.println();
    }
}