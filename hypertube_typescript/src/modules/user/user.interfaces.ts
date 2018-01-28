
import { Document } from 'mongoose'

export enum LANGS_AVAILABLE {
  EN = 'en',
  FR = 'fr'
}

export class Provider {
  name: string
  account: string
  token?: string
}

export class User extends Document {
  email: string
  password?: string
  providers?: Array<Provider>
  lang: LANGS_AVAILABLE
  firstname: string
  lastname: string
  picture?: string
}

export class createUserDTO {
  email: string
  password?: true
  provider?: Provider
  lang?: LANGS_AVAILABLE
  firstname: string
  lastname: string
}