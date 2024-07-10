package com.stt0504.Console.ChoiceActions;

import com.stt0504.Console.Action;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

/**
 * The Choice class represents an abstract action that presents a choice to the user.
 * It extends the Action class and provides methods to set a message, add choices, and allow the user to choose among them.
 * @param <T> The type of choices offered to the user.
 */
public abstract class Choice<T> extends Action {

    /** The message to display when presenting the choices. */
    private String message;

    /** The list of choices. */
    public List<T> choices = new ArrayList<>();

    /** The selected choice. */
    protected T choice;

    /** The converter used to convert choices to strings for display. */
    private Converter<T, String> converter;

    /**
     * Constructor for Choice class.
     * @param name The name of the choice action.
     */
    public Choice(String name) {
        super(name);
    }

    /**
     * Sets the message to display when presenting the choices.
     * @param message The message to display.
     */
    public void Message(String message) {
        this.message = message;
    }

    /**
     * Adds choices to the list of available choices.
     * @param choices The choices to add.
     */
    public void AddChoices(List<T> choices) {
        this.choices.addAll(choices);
    }

    /**
     * Sets the converter used to convert choices to strings for display.
     * @param converter The converter to use.
     */
    public void UseConverter(Converter<T, String> converter) {
        this.converter = converter;
    }

    /**
     * Presents the choices to the user and allows them to choose among them.
     */
    public void Choose() {
        System.out.println(message);
        for (int i = 0; i < choices.size(); i++) {
            System.out.println((i + 1) + ". " + converter.convert(choices.get(i)));
        }
        Scanner sc = new Scanner(System.in);

        int choice_number;

        choice_number = sc.nextInt();
        sc.nextLine();

        choice = choices.get(choice_number - 1);
    }
}
