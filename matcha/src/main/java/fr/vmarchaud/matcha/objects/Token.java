package fr.vmarchaud.matcha.objects;

import java.util.UUID;

import fr.vmarchaud.matcha.enums.EnumToken;
import lombok.Data;

@Data
public class Token {
	
	public UUID 		id;
	public UUID 		user;
	public EnumToken 	type;
	
}
