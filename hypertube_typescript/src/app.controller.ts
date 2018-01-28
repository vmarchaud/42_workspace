import { Get, Controller } from '@nestjs/common';
import * as pkg from '../package.json'
import { config } from './config'

@Controller()
export class AppController {
	@Get()
	root(): object {
    return {
      name: pkg.name,
      version: pkg.version,
      environment: config.ENV
    };
  }
}
