package com.stt0504;

import com.stt0504.Entities.Cat;
import com.stt0504.Entities.Owner;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.kafka.annotation.KafkaListener;
import org.springframework.kafka.core.KafkaTemplate;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;

@Service
public class OwnerService {
    private final OwnerDAO ownerDAO;
    private final KafkaTemplate<String, Object> template;
    @Autowired
    public OwnerService(OwnerDAO ownerDAO, KafkaTemplate<String, Object> template) {
        this.ownerDAO = ownerDAO;
        this.template = template;
    }

    public void addOwner(OwnerDTO owner) {
        if (owner.getName() == null || owner.getName().isEmpty()) {
            throw new IllegalArgumentException("Owner's name cannot be null");
        }
        ownerDAO.save(convert(owner));
    }

    @KafkaListener(topics = "get_all_owners", groupId = "owner_group")
    public List<OwnerDTO> getAllOwners() {
        List<Owner> owners = ownerDAO.findAll();
        List<OwnerDTO> result = owners.stream()
                .map(this::convert)
                .collect(Collectors.toList());
        template.send("send_all_owners", result);
        return result;
    }

    @KafkaListener(topics = "owner_get", groupId = "owner_group")
    public OwnerDTO getOwnerById(Long id) {
        Optional<Owner> optionalOwner = ownerDAO.findById(id);
        OwnerDTO result;
        if (optionalOwner.isPresent()) {
            result = convert(optionalOwner.get());
            template.send("owner_found", result);
            return result;
        } else {
            throw new IllegalArgumentException("Owner with id " + id + " is not found");
        }
    }


    public Owner convert(OwnerDTO owner) {
        return new Owner().setName(owner.getName())
                .setBirthDate(owner.getBirthDate());
    }

    public OwnerDTO convert(Owner owner) {
        return new OwnerDTO().setId(owner.getId())
                .setName(owner.getName())
                .setBirthDate(owner.getBirthDate())
                .setCatIds(owner.getCats().stream()
                .map(Cat::getId)
                .collect(Collectors.toList()));
    }
}
