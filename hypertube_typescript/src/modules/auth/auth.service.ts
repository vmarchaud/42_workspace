import { Model } from 'mongoose'
import { Component, Inject } from '@nestjs/common'
import { InjectModel } from '@nestjs/mongoose'
import { User, createUserDTO, Provider } from '../user/user.interfaces'
import { UserService } from '../user/user.service'
import * as bcrypt from 'bcryptjs'

@Component()
export class AuthService {
  constructor(private readonly userService: UserService) {}

  async findFromProvider (provider: Provider): Promise<User> {
    return await this.userService.find({ providers: { $elemMatch: provider } })
  }
}