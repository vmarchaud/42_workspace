import { Model } from 'mongoose'
import { Component, BadRequestException } from '@nestjs/common'
import { InjectModel } from '@nestjs/mongoose'
import { User, createUserDTO } from './user.interfaces'
import { UserSchema, UserValidator } from './user.schema'
import * as bcrypt from 'bcryptjs'

@Component()
export class UserService {
  constructor(@InjectModel(UserSchema) private readonly userModel: Model<User>) {}

  async create(user: createUserDTO): Promise<User> {
    const { error } = UserValidator.validate(user)
    if (error) {
      error.details = error.details.map(suberror => suberror.message)
      throw new BadRequestException(error)
    }
    // if the password has been set, hash it
    if (user.password) {
      const salt = bcrypt.genSaltSync(10)
      user.password = bcrypt.hashSync(user.password, salt)
    }
    const createdCat = new this.userModel(user)
    return await createdCat.save()
  }

  async findAll(): Promise<User[]> {
    return await this.userModel.find().exec()
  }

  async find(query) : Promise<User> {
    return await this.userModel.find(query).exec()
  }
}