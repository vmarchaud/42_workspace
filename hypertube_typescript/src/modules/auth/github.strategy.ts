import * as passport from 'passport'
import { Strategy } from 'passport-github'
import { Component, Inject } from '@nestjs/common'
import { AuthService } from './auth.service'
import { config } from '../../config'

@Component()
export class GithubStrategy extends Strategy {
  constructor(private readonly authService: AuthService) {
    super(
      {
        clientID: config.GITHUB_CLIENT_ID,
        clientSecret: config.GITHUB_CLIENT_SECRET,
        callbackURL: "http://127.0.0.1:3000/auth/github/callback"
      },
      async (req, payload, next) => await this.verify(req, payload, next)
    );
    passport.use('github', this);
  }

  public async verify(req, payload, done) {
    const isValid = await this.authService.isRegistered(payload);
    if (!isValid) {
      return done('Unauthorized', false);
    }
    done(null, payload);
  }
}