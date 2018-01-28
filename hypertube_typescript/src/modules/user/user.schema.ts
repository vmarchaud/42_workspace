
import * as mongoose from 'mongoose'
import * as Joi from 'joi'

export const UserSchema = new mongoose.Schema({
  email: {
    type: String,
    required: true,
    index: {
      unique: true
    }
  },
  providers: [
    {
      name: String,
      token: String
    }
  ],
  password: {
    type: String
  },
  lang: {
    type: String,
    default: 'en',
    enum: [ 'en', 'fr' ]
  },
  firstname: {
    type: String,
    required: true
  },
  lastname: {
    type: String,
    required: true
  },
  picture: {
    type: String
  }
});

export const UserValidator = Joi.object().keys({
  username: Joi.string().alphanum().min(6).max(30).required(),
  password: Joi.string().min(6),
  providers: Joi.array().items(Joi.object().keys({
    name: Joi.string().alphanum().required(),
    token: Joi.string(),
    account: Joi.string().required()
  })),
  firstname: Joi.string().alphanum().min(3).max(30).required(),
  lastname: Joi.string().alphanum().min(3).max(30).required(),
  lang: Joi.string().valid([ "en", "fr" ]),
  picture: Joi.string().base64(),
  email: Joi.string().email().required()
})
