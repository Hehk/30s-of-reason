type schema('a) = {
  .
  "resolvers": {. "Query": 'a},
  "typeDefs": string
};

type config('a) = {. "schema": schema('a)};

[@bs.module "apollo-link-schema"] [@bs.new]
external _make : config('a) => ReasonApolloTypes.apolloLink =
  "SchemaLink";

let make =_make;
