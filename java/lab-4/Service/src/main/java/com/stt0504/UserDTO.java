package com.stt0504;

import com.stt0504.Entities.Role;
import lombok.Getter;
import lombok.Setter;
import lombok.experimental.Accessors;

import java.util.Set;

@Getter
@Setter
@Accessors(chain = true)
public class UserDTO {
    private Long id;
    private String username;
    private String password;
    private boolean status;
    private Set<String> roles;
    private OwnerDTO owner;
}
