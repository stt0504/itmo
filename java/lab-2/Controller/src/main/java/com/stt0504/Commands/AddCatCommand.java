package com.stt0504.Commands;

import com.stt0504.*;

import java.time.LocalDate;
import java.util.Scanner;

public class AddCatCommand implements Command {
    private final CatService catService;

    public String getName() {
        return "Add a cat";
    }

    public AddCatCommand(CatService catService) {
        this.catService = catService;
    }

    @Override
    public void execute() {
        Scanner scanner = new Scanner(System.in);

        System.out.println();
        System.out.println("Enter information about the cat: ");

        System.out.print("Cat's name: ");
        String name = scanner.nextLine();

        System.out.print("Cat's birth date (yyyy-mm-dd): ");
        LocalDate birthDate = LocalDate.parse(scanner.nextLine());

        System.out.print("Cat's breed: ");
        String breed = scanner.nextLine();

        System.out.println("Choose cat's color:");
        for (ColorDTO color: ColorDTO.values()) {
            System.out.println((color.ordinal() + 1) + ". " + color.name());
        }

        System.out.print("Enter the number of the chosen color: ");
        int colorChoice = Integer.parseInt(scanner.nextLine());
        ColorDTO color = ColorDTO.values()[colorChoice - 1];

        System.out.print("Owner's ID: ");
        Long ownerId = Long.parseLong(scanner.nextLine());

        CatDTO cat = new CatDTO().setName(name)
                .setBirthDate(birthDate)
                .setBreed(breed)
                .setColor(color)
                .setOwnerId(ownerId);

        catService.addCat(cat);
        System.out.println();
    }
}