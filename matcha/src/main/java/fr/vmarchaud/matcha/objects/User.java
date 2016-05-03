package fr.vmarchaud.matcha.objects;

import java.util.Date;
import java.util.UUID;

import fr.vmarchaud.matcha.enums.EnumGender;
import fr.vmarchaud.matcha.enums.EnumState;
import lombok.Data;

@Data
public class User {
	
	private UUID 		id;
	private int			age;
	private String		name;
	private String 		firstname;
	private EnumGender 	gender;
	private String		bio;
	private String 		location;
	private UUID 		picture;
	private short 		score;
	private Date 		register_date;
	private EnumState 	state;
	private Date 		last_visit;

}
