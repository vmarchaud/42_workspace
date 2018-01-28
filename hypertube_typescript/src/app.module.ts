import { Module } from '@nestjs/common'
import { UserModule } from './modules/user/user.module'
import { AppController } from './app.controller'
import { MongooseModule } from '@nestjs/mongoose'
import { config } from './config'

@Module({
  imports: [
    MongooseModule.forRoot(config.MONGODB_URI),
    UserModule
  ],
  controllers: [
    AppController
  ],
  components: []
})
export class ApplicationModule {}
