import { Controller, Get, Post, Body, BadRequestException } from '@nestjs/common'
import { UserService } from './user.service'
import { User } from './user.interfaces'

@Controller('users')
export class UserController {
  constructor(private readonly userService: UserService) {}

  @Get('/')
	async findAll(): Promise<Object[]> {
    let users: User[] = await this.userService.findAll()
    return users.map(user => {
      return {
        lang: user.lang,
        picture: user.picture,
        firstname: user.firstname,
        lastname: user.lastname
      }
    })
  }

  @Post('/')
  async create(@Body() body): Promise<User> {
    if (!body.password) {
      throw new BadRequestException({
        name: "ValidationError",
        details: [
            "\"password\" is required"
        ]
      })
    }
    let user = await this.userService.create(body)
    return user
  }
}
