package com.stt0504;

import com.stt0504.Entities.User;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.kafka.annotation.KafkaListener;
import org.springframework.kafka.core.KafkaTemplate;
import org.springframework.security.core.annotation.AuthenticationPrincipal;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.web.bind.annotation.*;

import java.time.LocalDate;
import java.util.Arrays;
import java.util.List;
import java.util.concurrent.*;

@RestController
public class Controller {
    private final KafkaTemplate<String, Object> kafkaTemplate;
    private CompletableFuture<CatDTO> dtoCatFuture = new CompletableFuture<>();
    private CompletableFuture<List<CatDTO>> dtoCatListFuture = new CompletableFuture<>();
    private CompletableFuture<OwnerDTO> dtoOwnerFuture = new CompletableFuture<>();
    private CompletableFuture<List<OwnerDTO>> dtoOwnerListFuture = new CompletableFuture<>();

    private final UserDAO userDAO;
    @Autowired
    public Controller(KafkaTemplate<String, Object> kafkaTemplate, UserDAO userDAO) {
        this.kafkaTemplate = kafkaTemplate;
        this.userDAO = userDAO;
    }
    @KafkaListener(topics = "cat_found", groupId = "cat_group")
    public void listenForCatResponses(CatDTO dto) {
        dtoCatFuture.complete(dto);
    }

    @KafkaListener(topics = "send_cats_list", groupId = "cat_group")
    public void listenForListCatResponses(List<CatDTO> dtos) {
        dtoCatListFuture.complete(dtos);
    }

    @KafkaListener(topics = "send_added_cat", groupId = "cat_group")
    public void listenForAddCatResponse(CatDTO dto) {
        dtoCatFuture.complete(dto);
    }

    @KafkaListener(topics = "send_all_cats", groupId = "cat_group")
    public void listenForAllCatResponses(List<CatDTO> dtos) {
        dtoCatListFuture.complete(dtos);
    }
    @KafkaListener(topics = "send_all_owners", groupId = "owner_group")
    public void listenForAllOwnerResponses(List<OwnerDTO> dtos) {
        dtoOwnerListFuture.complete(dtos);
    }
    @KafkaListener(topics = "owner_found", groupId = "owner_group")
    public void listenForOwnerResponses(OwnerDTO dto) {
        dtoOwnerFuture.complete(dto);
    }
    @RequestMapping("/cats/get_by")
    public ResponseEntity<List<CatDTO>> getBy(@AuthenticationPrincipal UserDetails userDetails,
                                              @RequestParam(name = "color", required = false) String color,
                                              @RequestParam(name = "breed", required = false) String breed) throws ExecutionException, InterruptedException, TimeoutException {
        String username = userDetails.getUsername();
        User user = userDAO.findByUsername(username);
        long ownerId = user.getOwner().getId();
        List<String> filterDetails =  Arrays.asList(Long.toString(ownerId), color, breed);
        dtoCatListFuture = new CompletableFuture<>();
        kafkaTemplate.send("get_cats_by", filterDetails);
        List<CatDTO> result = dtoCatListFuture.get(5, TimeUnit.SECONDS);
        return ResponseEntity.ok(result);
    }

    @RequestMapping("/cats/all")
    public ResponseEntity<List<CatDTO>> getAllCats() throws ExecutionException, InterruptedException, TimeoutException {
        dtoCatListFuture = new CompletableFuture<>();
        kafkaTemplate.send("get_all_cats", null);
        List<CatDTO> result = dtoCatListFuture.get(5, TimeUnit.SECONDS);
        return ResponseEntity.ok(result);
    }

    @RequestMapping("/cats/get_by_id")
    public ResponseEntity<CatDTO> getCatById(@RequestParam(name = "id") Long id) throws ExecutionException, InterruptedException, TimeoutException {
        dtoCatFuture = new CompletableFuture<>();
        kafkaTemplate.send("cat_get", id);
        CatDTO result = dtoCatFuture.get(5, TimeUnit.SECONDS);
        return ResponseEntity.ok(result);
    }
    @RequestMapping("/owners/get_all")
    public ResponseEntity<List<OwnerDTO>> getOwners() throws ExecutionException, InterruptedException, TimeoutException {
        dtoOwnerListFuture = new CompletableFuture<>();
        kafkaTemplate.send("get_all_owners", null);
        List<OwnerDTO> result = dtoOwnerListFuture.get(5, TimeUnit.SECONDS);
        return ResponseEntity.ok(result);
    }

    @RequestMapping("/owners/get_by_id")
    public ResponseEntity<OwnerDTO> getOwnerById(@RequestParam(name = "id") Long id) throws ExecutionException, InterruptedException, TimeoutException {
        dtoOwnerFuture = new CompletableFuture<>();
        kafkaTemplate.send("owner_get", id);
        OwnerDTO result = dtoOwnerFuture.get(5, TimeUnit.SECONDS);
        return ResponseEntity.ok(result);
    }

    @RequestMapping("/cats/add")
    public ResponseEntity<CatDTO> addCat(@RequestParam(name = "name") String name,
                                         @RequestParam(name = "breed") String breed,
                                         @RequestParam(name = "color") String color) throws ExecutionException, InterruptedException, TimeoutException {
        dtoCatFuture = new CompletableFuture<>();
        List<String> parameters = Arrays.asList(
                name,
                breed,
                color
        );
        kafkaTemplate.send("add_cat", parameters);
        CatDTO result = dtoCatFuture.get(5, TimeUnit.SECONDS);
        return ResponseEntity.ok(result);
    }
}
