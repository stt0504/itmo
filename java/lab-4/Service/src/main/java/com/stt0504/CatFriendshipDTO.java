package com.stt0504;

import lombok.Getter;
import lombok.Setter;
import lombok.experimental.Accessors;

@Getter
@Setter
@Accessors(chain = true)
public class CatFriendshipDTO {
    private Long id;
    private Long catId;
    private Long friendId;
}
