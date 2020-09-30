<template>
  <div class="home">
    <h1>Junkyard Light Control</h1>
    <form>
      <div v-for="(value, name) in rooms" :key="name">
        <label for="room7">{{name}}</label>
        <v-select :options="value" label="name"></v-select>
      </div>
    </form>
  </div>
</template>

<script lang="ts">
import { Component, Vue } from 'vue-property-decorator'
import { Dictionary } from 'vue-router/types/router'
// import router from '../router'
// import HelloWorld from '@/components/HelloWorld.vue' // @ is an alias to /src
import vSelect from 'vue-select'
import 'vue-select/dist/vue-select.css'

Vue.component('v-select', vSelect)

export class Preset {
  public r?: number
  public g?: number
  public b?: number

  public name?: string

  constructor (name: string, r?: number, g?: number, b?: number) {
    this.name = name
    this.r = r
    this.g = g
    this.b = b
  }
}

@Component({
  components: {
  //  HelloWorld
  }
})
export default class Home extends Vue {
  rooms: Dictionary<Array<Preset>> = {
    '1st Floor Kitchen': [
      new Preset('Warm White', 255, 255, 100),
      new Preset('Cool White', 255, 255, 255),
      new Preset('Off', 0, 0, 0)
    ]
  }
}
</script>
