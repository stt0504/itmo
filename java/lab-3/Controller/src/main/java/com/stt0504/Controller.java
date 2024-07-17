package com.stt0504;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
public class Controller {
    private final CatService catService;
    private final OwnerService ownerService;

    @Autowired
    public Controller(CatService catService, OwnerService ownerService) {
        this.catService = catService;
        this.ownerService = ownerService;
    }

    @RequestMapping("/cats/all")
    public ResponseEntity<List<CatDTO>> getCats() {
        List<CatDTO> cats = catService.getAllCats();
        return new ResponseEntity<>(cats, HttpStatus.OK);
    }

    @RequestMapping("/cats/get_by_id")
    public ResponseEntity<CatDTO> getCatById(@RequestParam(name = "id") Long id) {
        CatDTO catDTO = catService.getById(id);
        return new ResponseEntity<>(catDTO, HttpStatus.OK);
    }

    @RequestMapping("/cats/get_by")
    public ResponseEntity<List<CatDTO>> getBy(@RequestParam(name = "owner_id", required = false) Long ownerId,
                                        @RequestParam(name = "color", required = false) String color,
                                        @RequestParam(name = "breed", required = false) String breed) {
        List<CatDTO> catDTO = catService.getBy(ownerId, color, breed);
        return new ResponseEntity<>(catDTO, HttpStatus.OK);
    }
    @RequestMapping("/owners/get_all")
    public ResponseEntity<List<OwnerDTO>> getOwners() {
        List<OwnerDTO> owners = ownerService.getOwners();
        return new ResponseEntity<>(owners, HttpStatus.OK);
    }

    @RequestMapping("/owners/get_by_id")
    public ResponseEntity<OwnerDTO> getOwnerById(@RequestParam(name = "id") Long id) {
        OwnerDTO ownerDTO = ownerService.getOwnerById(id);
        return new ResponseEntity<>(ownerDTO, HttpStatus.OK);
    }

    @RequestMapping("/cats/add_friendship")
    public ResponseEntity<List<CatFriendshipDTO>> addFriendship(@RequestParam(name = "id1") Long id1, @RequestParam("id2") Long id2) {
        List<CatFriendshipDTO> friendships = catService.addFriendship(id1, id2);
        return new ResponseEntity<>(friendships, HttpStatus.OK);
    }
}
