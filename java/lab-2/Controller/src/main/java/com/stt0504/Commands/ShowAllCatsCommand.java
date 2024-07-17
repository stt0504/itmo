package com.stt0504.Commands;

import com.stt0504.CatDTO;
import com.stt0504.CatService;

import java.util.List;

public class ShowAllCatsCommand implements Command {
    private final CatService catService;

    public String getName() {
        return "Show all cats";
    }
    public ShowAllCatsCommand(CatService catService) {
        this.catService = catService;
    }


    @Override
    public void execute() {
        System.out.println();
        List<CatDTO> cats = catService.getAllCats();

        for (CatDTO cat: cats) {
            System.out.println("--------------------------------");
            System.out.println("ID: " + cat.getId());
            showCatInfo(cat);
        }
        System.out.println("--------------------------------");
        System.out.println();
    }

    public void showCatInfo(CatDTO cat) {
        ShowCatInfoCommand.ShowCatInfo(cat, catService);
    }
}