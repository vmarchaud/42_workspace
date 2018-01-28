import { Module } from '@nestjs/common'
import { MongooseModule } from '@nestjs/mongoose'

import { AuthController } from './auth.controller'
import { AuthService } from './auth.service'
import { UserService } from '../user/user.service'
import { GithubStrategy } from './github.strategy'

@Module({
  imports: [
    UserService
  ],
  controllers: [
    AuthController
  ],
  components: [
    AuthService,
    GithubStrategy
  ],
  exports: [
    AuthService
  ]
})
export class AuthModule {}