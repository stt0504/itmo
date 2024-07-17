package com.stt0504;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.security.core.annotation.AuthenticationPrincipal;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.web.bind.annotation.*;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;
import java.util.Set;

@RestController
public class Controller {
    private final CatService catService;
    private final OwnerService ownerService;
    private final UserService userService;

    @Autowired
    public Controller(CatService catService, OwnerService ownerService, UserService userService) {
        this.catService = catService;
        this.ownerService = ownerService;
        this.userService = userService;
    }

    @RequestMapping("/cats/all") // admin
    public ResponseEntity<List<CatDTO>> getCats() {
        List<CatDTO> cats = catService.getAllCats();
        return new ResponseEntity<>(cats, HttpStatus.OK);
    }

    @RequestMapping("/cats/get_by_id") // admin
    public ResponseEntity<CatDTO> getCatById(@RequestParam(name = "id") Long id) {
        CatDTO catDTO = catService.getById(id);
        return new ResponseEntity<>(catDTO, HttpStatus.OK);
    }

    @RequestMapping("/cats/get_by")
    public ResponseEntity<List<CatDTO>> getBy(@AuthenticationPrincipal UserDetails userDetails,
                                        @RequestParam(name = "color", required = false) String color,
                                        @RequestParam(name = "breed", required = false) String breed) {
        String username = userDetails.getUsername();
        UserDTO user = userService.getUserByUsername(username);
        long ownerId = user.getOwner().getId();
        List<CatDTO> catDTO = catService.getBy(ownerId, color, breed);
        return new ResponseEntity<>(catDTO, HttpStatus.OK);
    }
    @RequestMapping("/owners/get_all") // admin
    public ResponseEntity<List<OwnerDTO>> getOwners() {
        List<OwnerDTO> owners = ownerService.getOwners();
        return new ResponseEntity<>(owners, HttpStatus.OK);
    }

    @RequestMapping("/owners/get_by_id") // admin
    public ResponseEntity<OwnerDTO> getOwnerById(@RequestParam(name = "id") Long id) {
        OwnerDTO ownerDTO = ownerService.getOwnerById(id);
        return new ResponseEntity<>(ownerDTO, HttpStatus.OK);
    }

    @RequestMapping("/cats/add_friendship") // admin
    public ResponseEntity<List<CatFriendshipDTO>> addFriendship(@RequestParam(name = "id1") Long id1, @RequestParam("id2") Long id2) {
        List<CatFriendshipDTO> friendships = catService.addFriendship(id1, id2);
        return new ResponseEntity<>(friendships, HttpStatus.OK);
    }

    @RequestMapping("/users/add_user") // admin
    public ResponseEntity<UserDTO> addUser(@RequestParam(name = "username") String username,
                                           @RequestParam(name = "password") String password,
                                           @RequestParam(name = "name") String name,
                                           @RequestParam(name = "birthdate") LocalDate birthdate)
    {
        OwnerDTO owner = new OwnerDTO().setName(name).setBirthDate(birthdate).setCatIds(new ArrayList<Long>());
        Set<String> roles = Set.of("USER");
        UserDTO user = new UserDTO().setUsername(username).setPassword(password).setOwner(owner).setRoles(roles);
        UserDTO result = userService.addUser(user);
        return new ResponseEntity<>(result, HttpStatus.OK);
    }
}
