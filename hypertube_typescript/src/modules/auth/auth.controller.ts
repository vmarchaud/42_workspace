import { Controller } from '@nestjs/common'
import { AuthService } from './auth.service'
import { Get } from '@nestjs/common'
import * as passport from 'passport'

@Controller('auth')
export class AuthController {
  constructor(private readonly authService: AuthService) {}

  @Get('github')
  async githubLogin() {
    return passport.authenticate('github')
  }

  @Get('github/callback')
  async githubCallback() {
    return passport.authenticate('github')
  }
}
