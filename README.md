# reason-react-todo

A simple learning project modeled after **[Jared Forsyth's ReasonReact tutorial](https://jaredforsyth.com/posts/a-reason-react-tutorial/)**.

Differences:

- styling with Bulma
- unique id for each item
- you can remove items
- you can edit items
- re-factored to use different modules/namespaces

**Live Demo on Github Pages: [reason-react-todo](https://sophiabrandt.github.io/reason-react-todo/)**.

**Build With:**

- [ReasonReact](https://reasonml.github.io/reason-react/) (JSX version 3, with hooks)
- [Bulma](https://bulma.io/)

## Run Project

```sh
npm install
npm start
```

## Format

```sh
npm format
```

This uses `refmt` to format all Reason files within the `src` folder.

## Build for Production

```sh
npm run build
```

This will replace the development artifact `build/Index.js` for an optimized version as well as copy `src/index.html` into `build/`. You can then deploy the contents of the `build` directory (`index.html` and `Index.js`).

If you make use of routing (via `ReasonReact.Router` or similar logic) ensure that server-side routing handles your routes or that 404's are directed back to `index.html` (which is how the dev server is set up).

**To enable dead code elimination**, change `bsconfig.json`'s `package-specs` `module` from `"commonjs"` to `"es6"`. Then re-run the above 2 commands. This will allow Webpack to remove unused code.
