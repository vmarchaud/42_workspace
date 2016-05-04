package fr.vmarchaud.matcha.objects;

import java.util.UUID;

import lombok.Data;

@Data
public class Image {
	
	public UUID			id;
	public UUID			user;
	public String		img;
	
}
