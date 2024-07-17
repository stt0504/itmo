package com.stt0504;

import com.stt0504.Dao.OwnerDAO;
import com.stt0504.Dao.UserDAO;
import com.stt0504.Entities.Role;
import com.stt0504.Entities.User;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.Optional;
import java.util.stream.Collectors;

@Service
public class UserService {
    private final UserDAO userDAO;
    private final OwnerDAO ownerDAO;

    @Autowired
    public UserService(UserDAO userDAO, OwnerDAO ownerDAO) {
        this.userDAO = userDAO;
        this.ownerDAO = ownerDAO;
    }

    public UserDTO addUser(UserDTO user) {
        if (user.getUsername() == null || user.getPassword() == null) {
            throw new IllegalArgumentException("Cat's name cannot be null");
        }
        User userEntity = convert(user);
        ownerDAO.save(userEntity.getOwner());
        return convert(userDAO.save(userEntity));
    }

    public UserDTO getUserByUsername(String username) {
        Optional<User> optionalUser = userDAO.findByUsername(username);
        if (optionalUser.isPresent()) {
            return convert(optionalUser.get());
        } else {
            throw new IllegalArgumentException("Owner with username " + username + " is not found");
        }
    }

    public User convert(UserDTO user) {
        return new User().setId(user.getId())
                .setOwner(OwnerService.convert(user.getOwner()))
                .setPassword(user.getPassword())
                .setRoles(user.getRoles().stream()
                        .map(Role::valueOf)
                        .collect(Collectors.toSet()))
                .setUsername(user.getUsername())
                .setStatus(user.isStatus());
    }

    public UserDTO convert(User user) {
        return new UserDTO().setId(user.getId())
                .setOwner(OwnerService.convert(user.getOwner()))
                .setPassword(user.getPassword())
                .setRoles(user.getRoles().stream()
                        .map(Enum::name)
                        .collect(Collectors.toSet()))
                .setUsername(user.getUsername())
                .setStatus(user.isStatus());
    }
}
