package com.stt0504.Commands;

import com.stt0504.OwnerDTO;
import com.stt0504.OwnerService;

import java.time.LocalDate;
import java.util.Scanner;

public class AddOwnerCommand implements Command {

    public String getName() {
        return "Add an owner";
    }
    private final OwnerService ownerService;

    public AddOwnerCommand(OwnerService ownerService) {
        this.ownerService = ownerService;
    }

    @Override
    public void execute() {
        Scanner scanner = new Scanner(System.in);
        System.out.println();
        System.out.println("Enter information about the cat owner: ");

        System.out.print("Owner's name: ");
        String name = scanner.nextLine();

        System.out.print("Owner's birth date (yyyy-mm-dd): ");
        LocalDate birthDate = LocalDate.parse(scanner.nextLine());


        OwnerDTO owner = new OwnerDTO().setName(name)
                .setBirthDate(birthDate);

        ownerService.addOwner(owner);
        System.out.println();
    }
}